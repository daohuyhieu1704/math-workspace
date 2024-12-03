#pragma once

#include "DisposableWrapper.h"
#include "OdDbEntity.h"
#include "UtilCLI.h"
#include <msclr/marshal_cppstd.h>
#define OD_ERROR_DEF(code, string) code,

using namespace System;
using namespace Geometry;

namespace MathGL
{
    public enum class MathResult
    {
		OD_ERROR_DEF(eOk, OD_T("No error"))
		OD_ERROR_DEF(eInvalidDrawing, OD_T("Invalid Drawing"))
		OD_ERROR_DEF(eNotImplementedYet, OD_T("Not implemented yet"))
		OD_ERROR_DEF(eNotApplicable, OD_T("Not Applicable"))
		OD_ERROR_DEF(eInvalidInput, OD_T("Invalid input"))
		OD_ERROR_DEF(eAmbiguousInput, OD_T("Ambiguous input"))
		OD_ERROR_DEF(eAmbiguousOutput, OD_T("Ambiguous output"))
		OD_ERROR_DEF(eOutOfMemory, OD_T("Out of memory"))
		OD_ERROR_DEF(eNoInterface, OD_T("No Interface"))
		OD_ERROR_DEF(eBufferTooSmall, OD_T("Buffer is too small"))
		OD_ERROR_DEF(eInvalidOpenState, OD_T("Invalid open state"))
		OD_ERROR_DEF(eUnsupportedMethod, OD_T("Unsupported method"))
		OD_ERROR_DEF(eEntityInInactiveLayout, OD_T("Entity is in inactive Layout"))
		OD_ERROR_DEF(eDuplicateHandle, OD_T("Handle already exists"))
		OD_ERROR_DEF(eNullHandle, OD_T("Null handle"))
		OD_ERROR_DEF(eBrokenHandle, OD_T("Broken handle"))
		OD_ERROR_DEF(eUnknownHandle, OD_T("Unknown handle"))
		OD_ERROR_DEF(eHandleInUse, OD_T("Handle in use"))
		OD_ERROR_DEF(eNullObjectPointer, OD_T("Null object pointer"))
		OD_ERROR_DEF(eNullObjectId, OD_T("Null object Id"))
		OD_ERROR_DEF(eNullBlockName, OD_T("Null Block m_name"))
		OD_ERROR_DEF(eContainerNotEmpty, OD_T("Container is not empty"))
		OD_ERROR_DEF(eNullEntityPointer, OD_T("Null entity pointer"))
		OD_ERROR_DEF(eIllegalEntityType, OD_T("Illegal entity type"))
		OD_ERROR_DEF(eKeyNotFound, OD_T("Key not found"))
		OD_ERROR_DEF(eDuplicateKey, OD_T("Duplicate key"))
		OD_ERROR_DEF(eInvalidIndex, OD_T("Invalid index"))
		OD_ERROR_DEF(eCharacterNotFound, OD_T("Character not found"))
		OD_ERROR_DEF(eDuplicateIndex, OD_T("Duplicate index"))
		OD_ERROR_DEF(eAlreadyInDb, OD_T("Already in Database"))
		OD_ERROR_DEF(eOutOfDisk, OD_T("Out of disk"))
		OD_ERROR_DEF(eDeletedEntry, OD_T("Deleted entry"))
		OD_ERROR_DEF(eNegativeValueNotAllowed, OD_T("Negative value not allowed"))
		OD_ERROR_DEF(eInvalidExtents, OD_T("Invalid extents"))
		OD_ERROR_DEF(eInvalidAdsName, OD_T("Invalid ads m_name"))
		OD_ERROR_DEF(eInvalidSymbolTableName, OD_T("Invalid Symbol Table m_name"))
		OD_ERROR_DEF(eInvalidKey, OD_T("Invalid key"))
		OD_ERROR_DEF(eWrongObjectType, OD_T("Wrong object type"))
		OD_ERROR_DEF(eWrongDatabase, OD_T("Wrong Database"))
		OD_ERROR_DEF(eObjectToBeDeleted, OD_T("Object to be deleted"))
		OD_ERROR_DEF(eInvalidFileVersion, OD_T("Invalid file version"))
		OD_ERROR_DEF(eAnonymousEntry, OD_T("Anonymous entry"))
		OD_ERROR_DEF(eIllegalReplacement, OD_T("Illegal replacement"))
		OD_ERROR_DEF(eEndOfObject, OD_T("End of oject"))
		OD_ERROR_DEF(eEndOfFile, OD_T("Unexpected end of file"))
		OD_ERROR_DEF(eFileExists, OD_T("File exists"))
		OD_ERROR_DEF(eCantOpenFile, OD_T("Can't open file"))
		OD_ERROR_DEF(eFileCloseError, OD_T("File close error"))
		OD_ERROR_DEF(eFileWriteError, OD_T("File write error"))
		OD_ERROR_DEF(eNoFileName, OD_T("No filename"))
		OD_ERROR_DEF(eFilerError, OD_T("Filer error"))
		OD_ERROR_DEF(eFileAccessErr, OD_T("File access error"))
		OD_ERROR_DEF(eFileSystemErr, OD_T("File system error"))
		OD_ERROR_DEF(eFileInternalErr, OD_T("File internal error"))
		OD_ERROR_DEF(eFileTooManyOpen, OD_T("Too many open files"))
		OD_ERROR_DEF(eFileNotFound, OD_T("File not found"))
		OD_ERROR_DEF(eUnknownFileType, OD_T("Unknown file type"))
		OD_ERROR_DEF(eIsReading, OD_T("Is reading"))
		OD_ERROR_DEF(eIsWriting, OD_T("Is writing"))
		OD_ERROR_DEF(eNotOpenForRead, OD_T("Not opened for read"))
		OD_ERROR_DEF(eNotOpenForWrite, OD_T("Not opened for write"))
		OD_ERROR_DEF(eNotThatKindOfClass, OD_T("Not that kind of class"))
		OD_ERROR_DEF(eInvalidBlockName, OD_T("Invalid Block m_name"))
		OD_ERROR_DEF(eMissingDxfField, OD_T("Missing dxf field"))
		OD_ERROR_DEF(eDuplicateDxfField, OD_T("Duplicate dxf field"))
		OD_ERROR_DEF(eInvalidGroupCode, OD_T("Invalid group code"))
		OD_ERROR_DEF(eInvalidResBuf, OD_T("Invalid ResBuf"))
		OD_ERROR_DEF(eBadDxfSequence, OD_T("Bad Dxf sequence"))
		OD_ERROR_DEF(eInvalidRoundTripR14Data, OD_T("Invalid RoundTripR14 data"))
		OD_ERROR_DEF(eVertexAfterFace, OD_T("Polyface Mesh vertex after face"))
		OD_ERROR_DEF(eInvalidVertexIndex, OD_T("Invalid vertex index"))
		OD_ERROR_DEF(eOtherObjectsBusy, OD_T("Other objects busy"))
		OD_ERROR_DEF(eMustFirstAddBlockToDb, OD_T("The invoked BlockTableRecord is not database-resident yet"))
		OD_ERROR_DEF(eCannotNestBlockDefs, OD_T("Cannot nest Block definitions"))
		OD_ERROR_DEF(eDwgRecoveredOK, OD_T(".dwg file recovered OK"))
		OD_ERROR_DEF(eDwgNotRecoverable, OD_T(".dwg file is not recoverable"))
		OD_ERROR_DEF(eDxfPartiallyRead, OD_T(".dxf file partially read"))
		OD_ERROR_DEF(eDxfReadAborted, OD_T(".dxf file read aborted"))
		OD_ERROR_DEF(eDxbPartiallyRead, OD_T(".dxb file partially read"))
		OD_ERROR_DEF(eDwgCRCError, OD_T("CRC does not match"))
		OD_ERROR_DEF(eDwgSentinelDoesNotMatch, OD_T("Sentinel does not match"))
		OD_ERROR_DEF(eDwgObjectImproperlyRead, OD_T("Object improperly read"))
		OD_ERROR_DEF(eNoInputFiler, OD_T("No input filer"))
		OD_ERROR_DEF(eDwgNeedsAFullSave, OD_T("Drawing needs a full save"))
		OD_ERROR_DEF(eDxbReadAborted, OD_T(".dxb file read aborted"))
		OD_ERROR_DEF(eDwkLockFileFound, OD_T("Dwk lock file found"))
		OD_ERROR_DEF(eWasErased, OD_T("Object was erased"))
		OD_ERROR_DEF(ePermanentlyErased, OD_T("Object was permanently erased"))
		OD_ERROR_DEF(eWasOpenForRead, OD_T("Was open for read"))
		OD_ERROR_DEF(eWasOpenForWrite, OD_T("Was open for write"))
		OD_ERROR_DEF(eWasOpenForUndo, OD_T("Was open for undo"))
		OD_ERROR_DEF(eWasNotifying, OD_T("Was notifying"))
		OD_ERROR_DEF(eWasOpenForNotify, OD_T("Was open for notify"))
		OD_ERROR_DEF(eOnLockedLayer, OD_T("On locked Layer"))
		OD_ERROR_DEF(eMustOpenThruOwner, OD_T("Must open thru owner"))
		OD_ERROR_DEF(eSubentitiesStillOpen, OD_T("Subentities still open"))
		OD_ERROR_DEF(eAtMaxReaders, OD_T("At max readers"))
		OD_ERROR_DEF(eIsWriteProtected, OD_T("Is write protected"))
		OD_ERROR_DEF(eIsXRefObject, OD_T("Is XRef object"))
		OD_ERROR_DEF(eNotAnEntity, OD_T("An object in entitiesToMove is not an entity"))
		OD_ERROR_DEF(eHadMultipleReaders, OD_T("Had multiple readers"))
		OD_ERROR_DEF(eInvalidBlkRecordName, OD_T("Invalid Symbol table record m_name"))
		OD_ERROR_DEF(eDuplicateRecordName, OD_T("Duplicate Record m_name"))
		OD_ERROR_DEF(eNotXrefBlock, OD_T("Symbol is not a Reference definition"))
		OD_ERROR_DEF(eEmptyRecordName, OD_T("Empty Record m_name"))
		OD_ERROR_DEF(eXRefDependent, OD_T("Symbol depend on other References"))
		OD_ERROR_DEF(eSelfReference, OD_T("Entity references itself"))
		OD_ERROR_DEF(eMissingSymbolTable, OD_T("Missing Symbol Table"))
		OD_ERROR_DEF(eMissingSymbolTableRec, OD_T("Missing Symbol Table record"))
		OD_ERROR_DEF(eWasNotOpenForWrite, OD_T("Was not open for write"))
		OD_ERROR_DEF(eCloseWasNotifying, OD_T("Close was notifying"))
		OD_ERROR_DEF(eCloseModifyAborted, OD_T("Close modify aborted"))
		OD_ERROR_DEF(eClosePartialFailure, OD_T("Close partial failure"))
		OD_ERROR_DEF(eCloseFailObjectDamaged, OD_T("Close fail object damaged"))
		OD_ERROR_DEF(eCannotBeErasedByCaller, OD_T("Object can't be erased"))
		OD_ERROR_DEF(eCannotBeResurrected, OD_T("Cannot be resurrected"))
		OD_ERROR_DEF(eInsertAfter, OD_T("Insert after"))
		OD_ERROR_DEF(eFixedAllErrors, OD_T("Fixed all errors"))
		OD_ERROR_DEF(eLeftErrorsUnfixed, OD_T("Left errors unfixed"))
		OD_ERROR_DEF(eUnrecoverableErrors, OD_T("Unrecoverable errors"))
		OD_ERROR_DEF(eNoDatabase, OD_T("No Database"))
		OD_ERROR_DEF(eXdataSizeExceeded, OD_T("XData size exceeded"))
		OD_ERROR_DEF(eCannotSaveHatchRoundtrip, OD_T("Cannot save Hatch roundtrip data due to format limitations (they are too large)"))
		OD_ERROR_DEF(eHatchHasInconsistentPatParams, OD_T("Hatch is gradient, but either solid fill flag not set or pattern type is not pre-defined"))
		OD_ERROR_DEF(eRegappIdNotFound, OD_T("Invalid RegApp"))
		OD_ERROR_DEF(eRepeatEntity, OD_T("Repeat entity"))
		OD_ERROR_DEF(eRecordNotInTable, OD_T("Record not in Table"))
		OD_ERROR_DEF(eIteratorDone, OD_T("Iterator done"))
		OD_ERROR_DEF(eNullIterator, OD_T("Null iterator"))
		OD_ERROR_DEF(eNotInBlock, OD_T("Not in symbol"))
		OD_ERROR_DEF(eOwnerNotInDatabase, OD_T("Owner not in Database"))
		OD_ERROR_DEF(eOwnerNotOpenForRead, OD_T("Owner not open for read"))
		OD_ERROR_DEF(eOwnerNotOpenForWrite, OD_T("Owner not open for write"))
		OD_ERROR_DEF(eExplodeBeforeTransform, OD_T("Explode before transform"))
		OD_ERROR_DEF(eCannotScaleNonOrtho, OD_T("Cannot transform by non-ortho matrix"))
		OD_ERROR_DEF(eCannotScaleNonUniformly, OD_T("Cannot transform by non-uniform scaling matrix"))
		OD_ERROR_DEF(eNotInDatabase, OD_T("Object not in Database"))
		OD_ERROR_DEF(eNotCurrentDatabase, OD_T("Not current Database"))
		OD_ERROR_DEF(eIsAnEntity, OD_T("Is an entity"))
		OD_ERROR_DEF(eCannotChangeActiveViewport, OD_T("Cannot change properties of active Viewport!"))
		OD_ERROR_DEF(eNotInPaperspace, OD_T("No active Viewport in Paper Space"))
		OD_ERROR_DEF(eCommandWasInProgress, OD_T("Command was in progress"))
		OD_ERROR_DEF(eGeneralModelingFailure, OD_T("General modeling failure"))
		OD_ERROR_DEF(eOutOfRange, OD_T("Out of range"))
		OD_ERROR_DEF(eNonCoplanarGeometry, OD_T("Non coplanar geometry"))
		OD_ERROR_DEF(eDegenerateGeometry, OD_T("Degenerate geometry"))
		OD_ERROR_DEF(eInvalidAxis, OD_T("Invalid axis"))
		OD_ERROR_DEF(ePointNotOnEntity, OD_T("Point not on entity"))
		OD_ERROR_DEF(eSingularPoint, OD_T("Singular point"))
		OD_ERROR_DEF(eInvalidOffset, OD_T("Invalid offset"))
		OD_ERROR_DEF(eNonPlanarEntity, OD_T("Non planar entity"))
		OD_ERROR_DEF(eCannotExplodeEntity, OD_T("Can not explode entity"))
		OD_ERROR_DEF(eStringTooLong, OD_T("String too long"))
		OD_ERROR_DEF(eInvalidSymTableFlag, OD_T("Invalid Symbol Table flag"))
		OD_ERROR_DEF(eUndefinedLineType, OD_T("Undefined LineStyle"))
		OD_ERROR_DEF(eInvalidTextStyle, OD_T("TextStyle is invalid"))
		OD_ERROR_DEF(eTooFewLineTypeElements, OD_T("Too few LineType elements"))
		OD_ERROR_DEF(eTooManyLineTypeElements, OD_T("Too many LineType elements"))
		OD_ERROR_DEF(eExcessiveItemCount, OD_T("Excessive item count"))
		OD_ERROR_DEF(eIgnoredLinetypeRedef, OD_T("Ignored LineType redefinition"))
		OD_ERROR_DEF(eBadUCS, OD_T("Bad UCS"))
		OD_ERROR_DEF(eBadPaperspaceView, OD_T("Bad Paper Space View"))
		OD_ERROR_DEF(eSomeInputDataLeftUnread, OD_T("Some input data left unread"))
		OD_ERROR_DEF(eNoInternalSpace, OD_T("No internal space"))
		OD_ERROR_DEF(eInvalidDimStyle, OD_T("Invalid DimensionStyle"))
		OD_ERROR_DEF(eInvalidLayer, OD_T("Invalid Layer"))
		OD_ERROR_DEF(eInvalidMlineStyle, OD_T("RlineStyle is invalid"))
		OD_ERROR_DEF(eDwgNeedsRecovery, OD_T(".dwg file needs recovery"))
		OD_ERROR_DEF(eRecoveryFailed, OD_T("Recovery failed"))
		OD_ERROR_DEF(eDeleteEntity, OD_T("Delete entity"))
		OD_ERROR_DEF(eInvalidFix, OD_T("Invalid fix"))
		OD_ERROR_DEF(eBadLayerName, OD_T("Bad Layer m_name"))
		OD_ERROR_DEF(eLayerGroupCodeMissing, OD_T("Layer group code missing"))
		OD_ERROR_DEF(eBadColor, OD_T("Bad color"))
		OD_ERROR_DEF(eBadColorIndex, OD_T("Bad color index"))
		OD_ERROR_DEF(eBadLinetypeName, OD_T("Bad LineType m_name"))
		OD_ERROR_DEF(eBadLinetypeScale, OD_T("Bad LineType scale"))
		OD_ERROR_DEF(eBadVisibilityValue, OD_T("Bad visibility value"))
		OD_ERROR_DEF(eProperClassSeparatorExpected, OD_T("Proper class separator expected"))
		OD_ERROR_DEF(eBadLineWeightValue, OD_T("Bad lineweight value"))
		OD_ERROR_DEF(ePagerError, OD_T("Pager error"))
		OD_ERROR_DEF(eOutOfPagerMemory, OD_T("Out of pager memory"))
		OD_ERROR_DEF(ePagerWriteError, OD_T("Pager write error"))
		OD_ERROR_DEF(eWasNotForwarding, OD_T("Was not forwarding"))
		OD_ERROR_DEF(eInvalidIdMap, OD_T("Invalid Id map"))
		OD_ERROR_DEF(eInvalidOwnerObject, OD_T("Invalid owner Object"))
		OD_ERROR_DEF(eOwnerNotSet, OD_T("Owner not set"))
		OD_ERROR_DEF(eWrongSubentityType, OD_T("Wrong subentity type"))
		OD_ERROR_DEF(eTooManyVertices, OD_T("Too many vertices"))
		OD_ERROR_DEF(eTooFewVertices, OD_T("Too few vertices"))
		OD_ERROR_DEF(eNoActiveTransactions, OD_T("No active transactions"))
		OD_ERROR_DEF(eTransactionIsActive, OD_T("Transaction is active"))
		OD_ERROR_DEF(eNotTopTransaction, OD_T("Not top transaction"))
		OD_ERROR_DEF(eTransactionOpenWhileCommandEnded, OD_T("Transaction open while command ended"))
		OD_ERROR_DEF(eInProcessOfCommitting, OD_T("In process of committing"))
		OD_ERROR_DEF(eNotNewlyCreated, OD_T("Not newly created object"))
		OD_ERROR_DEF(eLongTransReferenceError, OD_T("Entity is excluded from long transaction"))
		OD_ERROR_DEF(eNoWorkSet, OD_T("No work set"))
		OD_ERROR_DEF(eAlreadyInGroup, OD_T("Entity already in group"))
		OD_ERROR_DEF(eNotInGroup, OD_T("There is no entity with this Id in group"))
		OD_ERROR_DEF(eBadDwgFile, OD_T("Bad .dwg file"))
		OD_ERROR_DEF(eInvalidREFIID, OD_T("Invalid REFIID"))
		OD_ERROR_DEF(eInvalidNormal, OD_T("Invalid normal"))
		OD_ERROR_DEF(eInvalidStyle, OD_T("Invalid Style"))
		OD_ERROR_DEF(eCannotRestoreFromAcisFile, OD_T("Cannot restore from Acis file"))
		OD_ERROR_DEF(eEmptyAcisFile, OD_T("Empty ACIS not allowed"))
		OD_ERROR_DEF(eNLSFileNotAvailable, OD_T("NLS file not available"))
		OD_ERROR_DEF(eNotAllowedForThisProxy, OD_T("Not allowed for this proxy"))
		OD_ERROR_DEF(eNotSupportedInDwgApi, OD_T("Not supported in API"))
		OD_ERROR_DEF(ePolyWidthLost, OD_T("Poly width lost"))
		OD_ERROR_DEF(eNullExtents, OD_T("Null extents"))
		OD_ERROR_DEF(eExplodeAgain, OD_T("Explode again"))
		OD_ERROR_DEF(eBadDwgHeader, OD_T("Bad .dwg file header"))
		OD_ERROR_DEF(eLockViolation, OD_T("Lock violation"))
		OD_ERROR_DEF(eLockConflict, OD_T("Lock conflict"))
		OD_ERROR_DEF(eDatabaseObjectsOpen, OD_T("Database objects open"))
		OD_ERROR_DEF(eLockChangeInProgress, OD_T("Lock change in progress"))
		OD_ERROR_DEF(eVetoed, OD_T("Vetoed"))
		OD_ERROR_DEF(eNoDocument, OD_T("ODAX no document"))
		OD_ERROR_DEF(eNotFromThisDocument, OD_T("Not from this document"))
		OD_ERROR_DEF(eLISPActive, OD_T("LISP active"))
		OD_ERROR_DEF(eTargetDocNotQuiescent, OD_T("Target doc not quiescent"))
		OD_ERROR_DEF(eDocumentSwitchDisabled, OD_T("Document switch disabled"))
		OD_ERROR_DEF(eInvalidContext, OD_T("Invalid context of execution"))
		OD_ERROR_DEF(eCreateFailed, OD_T("Create failed"))
		OD_ERROR_DEF(eCreateInvalidName, OD_T("Create invalid m_name"))
		OD_ERROR_DEF(eSetFailed, OD_T("Setting active Layout failed"))
		OD_ERROR_DEF(eDelDoesNotExist, OD_T("Does not exist"))
		OD_ERROR_DEF(eDelIsModelSpace, OD_T("Model Space Layout can't be deleted"))
		OD_ERROR_DEF(eDelLastLayout, OD_T("Last Paper Space Layout can't be deleted"))
		OD_ERROR_DEF(eDelUnableToSetCurrent, OD_T("Unable to delete current"))
		OD_ERROR_DEF(eDelUnableToFind, OD_T("Unable to find to delete"))
		OD_ERROR_DEF(eRenameDoesNotExist, OD_T("Cannot rename non-existing"))
		OD_ERROR_DEF(eRenameIsModelSpace, OD_T("Model Space Layout can't be renamed"))
		OD_ERROR_DEF(eRenameInvalidLayoutName, OD_T("Invalid Layout m_name"))
		OD_ERROR_DEF(eRenameLayoutAlreadyExists, OD_T("Layout already exists"))
		OD_ERROR_DEF(eRenameInvalidName, OD_T("Cannot rename: the m_name is invalid"))
		OD_ERROR_DEF(eCopyDoesNotExist, OD_T("Copy failed: object does not exist"))
		OD_ERROR_DEF(eCopyIsModelSpace, OD_T("Cannot copy Model Space"))
		OD_ERROR_DEF(eCopyFailed, OD_T("Copy failed"))
		OD_ERROR_DEF(eCopyInvalidName, OD_T("Copy failed: invalid m_name"))
		OD_ERROR_DEF(eCopyNameExists, OD_T("Copy failed: such m_name already exists"))
		OD_ERROR_DEF(eProfileDoesNotExist, OD_T("Profile does not exist"))
		OD_ERROR_DEF(eInvalidProfileName, OD_T("Invalid profile m_name"))
		OD_ERROR_DEF(eProfileIsInUse, OD_T("Profile is in use"))
		OD_ERROR_DEF(eRegistryAccessError, OD_T("Registry access error"))
		OD_ERROR_DEF(eRegistryCreateError, OD_T("Registry create error"))
		OD_ERROR_DEF(eBadDxfFile, OD_T("Bad Dxf file"))
		OD_ERROR_DEF(eUnknownDxfFileFormat, OD_T("Unknown Dxf file format"))
		OD_ERROR_DEF(eMissingDxfSection, OD_T("Missing Dxf section"))
		OD_ERROR_DEF(eInvalidDxfSectionName, OD_T("Invalid Dxf section m_name"))
		OD_ERROR_DEF(eNotDxfHeaderGroupCode, OD_T("Not Dxf header group code"))
		OD_ERROR_DEF(eUndefinedDxfGroupCode, OD_T("Undefined Dxf group code"))
		OD_ERROR_DEF(eNotInitializedYet, OD_T("Not initialized yet"))
		OD_ERROR_DEF(eInvalidDxf2dPoint, OD_T("Invalid Dxf 2d point"))
		OD_ERROR_DEF(eInvalidDxf3dPoint, OD_T("Invalid Dxf 3d point"))
		OD_ERROR_DEF(eBadlyNestedAppData, OD_T("Badly nested AppData"))
		OD_ERROR_DEF(eIncompleteBlockDefinition, OD_T("Incomplete Block definition"))
		OD_ERROR_DEF(eIncompleteComplexObject, OD_T("Incomplete complex object"))
		OD_ERROR_DEF(eBlockDefInEntitySection, OD_T("Block definition in entity section"))
		OD_ERROR_DEF(eNoBlockBegin, OD_T("No symbol begin"))
		OD_ERROR_DEF(eDuplicateLayerName, OD_T("Duplicate Layer m_name"))
		OD_ERROR_DEF(eBadPlotStyleName, OD_T("Bad PrintStyle m_name"))
		OD_ERROR_DEF(eDuplicateBlockName, OD_T("Duplicate Block m_name"))
		OD_ERROR_DEF(eBadPlotStyleType, OD_T("Bad PlotStyle type"))
		OD_ERROR_DEF(eBadPlotStyleNameHandle, OD_T("Bad PlotStyle m_name handle"))
		OD_ERROR_DEF(eUndefineShapeName, OD_T("Undefined Shape m_name"))
		OD_ERROR_DEF(eDuplicateBlockDefinition, OD_T("Duplicate Block definition"))
		OD_ERROR_DEF(eMissingBlockName, OD_T("Missing Block m_name"))
		OD_ERROR_DEF(eBinaryDataSizeExceeded, OD_T("Binary data size exceeded"))
		OD_ERROR_DEF(eObjectIsReferenced, OD_T("Object is referenced"))
		OD_ERROR_DEF(eInvalidThumbnailBitmap, OD_T("Invalid thumbnail bitmap"))
		OD_ERROR_DEF(eDuplicateName, OD_T("Duplicate m_name"))
		OD_ERROR_DEF(eGuidNoAddress, OD_T("eGuidNoAddress"))
		OD_ERROR_DEF(eMustBe0to2, OD_T("Must be 0 to 2"))
		OD_ERROR_DEF(eMustBe0to3, OD_T("Must be 0 to 3"))
		OD_ERROR_DEF(eMustBe0to4, OD_T("Must be 0 to 4"))
		OD_ERROR_DEF(eMustBe0to5, OD_T("Must be 0 to 5"))
		OD_ERROR_DEF(eMustBe0to8, OD_T("Must be 0 to 8"))
		OD_ERROR_DEF(eMustBe1to8, OD_T("Must be 1 to 8"))
		OD_ERROR_DEF(eMustBe1to15, OD_T("Must be 1 to 15"))
		OD_ERROR_DEF(eMustBePositive, OD_T("Must be positive"))
		OD_ERROR_DEF(eMustBeNonNegative, OD_T("Must be non negative"))
		OD_ERROR_DEF(eMustBeNonZero, OD_T("Must be non zero"))
		OD_ERROR_DEF(eMustBe1to6, OD_T("Must be 1 to 6"))
		OD_ERROR_DEF(eNoPlotStyleTranslationTable, OD_T("No PlotStyle translation table"))
		OD_ERROR_DEF(ePlotStyleInColorDependentMode, OD_T("PrintStyle is in color dependent mode"))
		OD_ERROR_DEF(eMaxLayouts, OD_T("Max Layouts"))
		OD_ERROR_DEF(eNoClassId, OD_T("No ClassId"))
		OD_ERROR_DEF(eUndoOperationNotAvailable, OD_T("Undo operation is not available"))
		OD_ERROR_DEF(eUndoNoGroupBegin, OD_T("No undo group begin"))
		OD_ERROR_DEF(eHatchTooDense, OD_T("Hatch is too dense - ignoring"))
		OD_ERROR_DEF(eOpenFileCancelled, OD_T("File open cancelled"))
		OD_ERROR_DEF(eNotHandled, OD_T("Not handled"))
		OD_ERROR_DEF(eLibIntegrityBroken, OD_T("Library integrity is broken"))
		OD_ERROR_DEF(eAlreadyActive, OD_T("Already active"))
		OD_ERROR_DEF(eAlreadyInactive, OD_T("Already inactive"))
		OD_ERROR_DEF(eCodepageNotFound, OD_T("Codepage not found"))
		OD_ERROR_DEF(eIncorrectInitFileVersion, OD_T("Incorrect init file version"))
		OD_ERROR_DEF(eInternalFreetypeError, OD_T("Internal error in Freetype font library"))
		OD_ERROR_DEF(eNoUCSPresent, OD_T("No CoordinateSystem present in entity"))
		OD_ERROR_DEF(eBadObjType, OD_T("Object has wrong type"))
		OD_ERROR_DEF(eBadProtocolExtension, OD_T("Protocol extension object is bad"))
		OD_ERROR_DEF(eHatchInvalidPatternName, OD_T("Bad m_name for Hatch pattern"))
		OD_ERROR_DEF(eNotTransactionResident, OD_T("Object is not transaction resident"))
		OD_ERROR_DEF(eDwgFileIsEncrypted, OD_T(".dwg file is encrypted"))
		OD_ERROR_DEF(eInvalidPassword, OD_T("The password is incorrect"))
		OD_ERROR_DEF(eDecryptionError, OD_T("HostApp cannot decrypt data"))
		OD_ERROR_DEF(eArithmeticOverflow, OD_T("An arithmetic overflow"))
		OD_ERROR_DEF(eSkipObjPaging, OD_T("Paging skips the object"))
		OD_ERROR_DEF(eStopPaging, OD_T("Paging is stoped"))
		OD_ERROR_DEF(eInvalidDimStyleResBufData, OD_T("Invalid ResBuf with DimensionStyle data"))
		OD_ERROR_DEF(eExtendedError, OD_T("Extended error"))
		OD_ERROR_DEF(eGripOpFailure, OD_T("The grip operation has failed"))
		OD_ERROR_DEF(eGripOpNoRedrawGrip, OD_T("NoRedrawGrip"))
		OD_ERROR_DEF(eGripOpGripHotToWarm, OD_T("GripHotToWarm"))
		OD_ERROR_DEF(eGripOpGetNewGripPoints, OD_T("GetNewGripPoints"))
		OD_ERROR_DEF(eUnsupportedEarlyDwgVersion, OD_T("Unsupported early .dwg file version"))
		OD_ERROR_DEF(eCannotChangeColumnType, OD_T("Cannot change column type"))
		OD_ERROR_DEF(eCustomSizeNotPossible, OD_T("Custom size not possible"))
		OD_ERROR_DEF(eDataLinkAdapterNotFound, OD_T("DataLink adapter not found"))
		OD_ERROR_DEF(eDataLinkInvalidAdapterId, OD_T("DataLink invalid adapter id"))
		OD_ERROR_DEF(eDataLinkNotFound, OD_T("DataLink not found"))
		OD_ERROR_DEF(eDataLinkBadConnectionString, OD_T("DataLink bad connection string"))
		OD_ERROR_DEF(eDataLinkNotUpdatedYet, OD_T("DataLink not updated yet"))
		OD_ERROR_DEF(eDataLinkSourceNotFound, OD_T("DataLink source not found"))
		OD_ERROR_DEF(eDataLinkConnectionFailed, OD_T("DataLink connection failed"))
		OD_ERROR_DEF(eDataLinkSourceUpdateNotAllowed, OD_T("DataLink source update not allowed"))
		OD_ERROR_DEF(eDataLinkSourceIsWriteProtected, OD_T("DataLink source is write protected"))
		OD_ERROR_DEF(eDataLinkExcelNotFound, OD_T("DataLink excel not found"))
		OD_ERROR_DEF(eDataLinkOtherError, OD_T("DataLink other error"))
		OD_ERROR_DEF(eDeviceNotFound, OD_T("Device not found"))
		OD_ERROR_DEF(eDwgCrcDoesNotMatch, OD_T("CRC does not match"))
		OD_ERROR_DEF(eDwgShareDemandLoad, OD_T(".dwg file share demand load"))
		OD_ERROR_DEF(eDwgShareReadAccess, OD_T(".dwg file share read access"))
		OD_ERROR_DEF(eDwgShareWriteAccess, OD_T(".dwg file share write access"))
		OD_ERROR_DEF(eFileMissingSections, OD_T("Missing section"))
		OD_ERROR_DEF(eFileSharingViolation, OD_T("File sharing violation"))
		OD_ERROR_DEF(eFiniteStateMachineError, OD_T("Finite state machine error"))
		OD_ERROR_DEF(eGraphicsNotGenerated, OD_T("Graphics not generated"))
		OD_ERROR_DEF(eHandleExists, OD_T("Handle exists"))
		OD_ERROR_DEF(eIgnoredLinetypeRedefinition, OD_T("Ignored LineType redefinition"))
		OD_ERROR_DEF(eIncompatiblePlotSettings, OD_T("Incompatible PlotSettings"))
		OD_ERROR_DEF(eInternetBadPath, OD_T("Bad path"))
		OD_ERROR_DEF(eInternetBase, OD_T("Base"))
		OD_ERROR_DEF(eInternetCreateInternetSessionFailed, OD_T("CreateInternetSessionFailed"))
		OD_ERROR_DEF(eInternetDirectoryFull, OD_T("DirectoryFull              "))
		OD_ERROR_DEF(eInternetDiskFull, OD_T("DiskFull                   "))
		OD_ERROR_DEF(eInternetFileAccessDenied, OD_T("FileAccessDenied           "))
		OD_ERROR_DEF(eInternetFileGenericError, OD_T("FileGenericError           "))
		OD_ERROR_DEF(eInternetFileNotFound, OD_T("FileNotFound               "))
		OD_ERROR_DEF(eInternetFileOpenFailed, OD_T("FileOpenFailed             "))
		OD_ERROR_DEF(eInternetGenericException, OD_T("GenericException           "))
		OD_ERROR_DEF(eInternetHardwareError, OD_T("HardwareError              "))
		OD_ERROR_DEF(eInternetHttpAccessDenied, OD_T("HttpAccessDenied           "))
		OD_ERROR_DEF(eInternetHttpBadGateway, OD_T("HttpBadGateway             "))
		OD_ERROR_DEF(eInternetHttpBadMethod, OD_T("HttpBadMethod              "))
		OD_ERROR_DEF(eInternetHttpBadRequest, OD_T("HttpBadRequest             "))
		OD_ERROR_DEF(eInternetHttpConflict, OD_T("HttpConflict               "))
		OD_ERROR_DEF(eInternetHttpGatewayTimeout, OD_T("HttpGatewayTimeout         "))
		OD_ERROR_DEF(eInternetHttpLengthRequired, OD_T("HttpLengthRequired         "))
		OD_ERROR_DEF(eInternetHttpNoAcceptableResponse, OD_T("HttpNoAcceptableResponse   "))
		OD_ERROR_DEF(eInternetHttpNotSupported, OD_T("HttpNotSupported           "))
		OD_ERROR_DEF(eInternetHttpObjectNotFound, OD_T("HttpObjectNotFound         "))
		OD_ERROR_DEF(eInternetHttpOpenRequestFailed, OD_T("HttpOpenRequestFailed      "))
		OD_ERROR_DEF(eInternetHttpPaymentRequired, OD_T("HttpPaymentRequired        "))
		OD_ERROR_DEF(eInternetHttpPreconditionFailure, OD_T("HttpPreconditionFailure    "))
		OD_ERROR_DEF(eInternetHttpProxyAuthorizationRequired, OD_T("HttpProxyAuthorizationRequired "))
		OD_ERROR_DEF(eInternetHttpRequestForbidden, OD_T("HttpRequestForbidden           "))
		OD_ERROR_DEF(eInternetHttpRequestTooLarge, OD_T("HttpRequestTooLarge            "))
		OD_ERROR_DEF(eInternetHttpResourceGone, OD_T("HttpResourceGone               "))
		OD_ERROR_DEF(eInternetHttpServerError, OD_T("HttpServerError                "))
		OD_ERROR_DEF(eInternetHttpServiceUnavailable, OD_T("HttpServiceUnavailable         "))
		OD_ERROR_DEF(eInternetHttpTimedOut, OD_T("HttpTimedOut                   "))
		OD_ERROR_DEF(eInternetHttpUnsupportedMedia, OD_T("HttpUnsupportedMedia           "))
		OD_ERROR_DEF(eInternetHttpUriTooLong, OD_T("HttpUriTooLong                 "))
		OD_ERROR_DEF(eInternetHttpVersionNotSupported, OD_T("HttpVersionNotSupported        "))
		OD_ERROR_DEF(eInternetInCache, OD_T("InCache                        "))
		OD_ERROR_DEF(eInternetInternetError, OD_T("InternetError                  "))
		OD_ERROR_DEF(eInternetInternetSessionConnectFailed, OD_T("InternetSessionConnectFailed   "))
		OD_ERROR_DEF(eInternetInternetSessionOpenFailed, OD_T("InternetSessionOpenFailed      "))
		OD_ERROR_DEF(eInternetInvalidAccessType, OD_T("InvalidAccessType              "))
		OD_ERROR_DEF(eInternetInvalidFileHandle, OD_T("InvalidFileHandle              "))
		OD_ERROR_DEF(eInternetNoInternetSupport, OD_T("NoInternetSupport              "))
		OD_ERROR_DEF(eInternetNotAnUrl, OD_T("NotAnUrl                       "))
		OD_ERROR_DEF(eInternetNotImplemented, OD_T("NotImplemented                 "))
		OD_ERROR_DEF(eInternetNoWinInternet, OD_T("NoWinInternet                  "))
		OD_ERROR_DEF(eInternetOK, OD_T("OK                             "))
		OD_ERROR_DEF(eInternetOldWinInternet, OD_T("OldWinInternet                 "))
		OD_ERROR_DEF(eInternetProtocolNotSupported, OD_T("ProtocolNotSupported           "))
		OD_ERROR_DEF(eInternetSharingViolation, OD_T("SharingViolation               "))
		OD_ERROR_DEF(eInternetTooManyOpenFiles, OD_T("TooManyOpenFiles               "))
		OD_ERROR_DEF(eInternetUnknownError, OD_T("UnknownError                   "))
		OD_ERROR_DEF(eInternetUserCancelledTransfer, OD_T("UserCancelledTransfer          "))
		OD_ERROR_DEF(eInternetValidUrl, OD_T("Valid URL"))
		OD_ERROR_DEF(eInvalidEngineState, OD_T("Invalid engine state"))
		OD_ERROR_DEF(eInvalidFaceVertexIndex, OD_T("Invalid Face vertex index"))
		OD_ERROR_DEF(eInvalidFileExtension, OD_T("Invalid file extension"))
		OD_ERROR_DEF(eInvalidMeshVertexIndex, OD_T("Invalid Mesh vertex index"))
		OD_ERROR_DEF(eInvalidObjectId, OD_T("Invalid object Id"))
		OD_ERROR_DEF(eInvalidPlotArea, OD_T("Invalid plot area"))
		OD_ERROR_DEF(eInvalidPlotInfo, OD_T("Invalid plot info"))
		OD_ERROR_DEF(eInvalidView, OD_T("Invalid View"))
		OD_ERROR_DEF(eInvalidWindowArea, OD_T("Invalid window area"))
		OD_ERROR_DEF(eInvalidXrefObjectId, OD_T("Invalid Xref object Id"))
		OD_ERROR_DEF(eLayoutNotCurrent, OD_T("Layout not current"))
		OD_ERROR_DEF(eMakeMeProxyAndResurrect, OD_T("Make me proxy and resurrect"))
		OD_ERROR_DEF(eMustPlotToFile, OD_T("Must plot to file"))
		OD_ERROR_DEF(eCannotPlotToFile, OD_T("Cannot plot to file"))
		OD_ERROR_DEF(eNoCurrentConfig, OD_T("No current config"))
		OD_ERROR_DEF(eNoErrorHandler, OD_T("No error handler"))
		OD_ERROR_DEF(eNoLabelBlock, OD_T("No label Block"))
		OD_ERROR_DEF(eNoLayout, OD_T("No Layout"))
		OD_ERROR_DEF(eNoMatchingMedia, OD_T("No matching media"))
		OD_ERROR_DEF(eNonePlotDevice, OD_T("None plot device"))
		OD_ERROR_DEF(eNoThumbnailBitmap, OD_T("No thumbnail bitmap"))
		OD_ERROR_DEF(eNotMultiPageCapable, OD_T("Not multipage capable"))
		OD_ERROR_DEF(eNoViewAssociation, OD_T("No View association"))
		OD_ERROR_DEF(eNullPtr, OD_T("Null Ptr"))
		OD_ERROR_DEF(eNumberOfCopiesNotSupported, OD_T("Number of copies not supported"))
		OD_ERROR_DEF(eObsoleteFileFormat, OD_T("Obsolete file format"))
		OD_ERROR_DEF(ePageCancelled, OD_T("Page cancelled"))
		OD_ERROR_DEF(ePlotAlreadyStarted, OD_T("Plot already started"))
		OD_ERROR_DEF(ePlotCancelled, OD_T("Plot cancelled"))
		OD_ERROR_DEF(eRepeatedDwgRead, OD_T("Repeated .dwg file read"))
		OD_ERROR_DEF(eRowsMustMatchColumns, OD_T("Rows must match columns"))
		OD_ERROR_DEF(eSecErrorCipherNotSupported, OD_T("Error cipher not supported"))
		OD_ERROR_DEF(eSecErrorComputingSignature, OD_T("Error computing signature"))
		OD_ERROR_DEF(eSecErrorDecryptingData, OD_T("Error decrypting data"))
		OD_ERROR_DEF(eSecErrorEncryptingData, OD_T("Error encrypting data"))
		OD_ERROR_DEF(eSecErrorGeneratingTimestamp, OD_T("Error generating timestamp"))
		OD_ERROR_DEF(eSecErrorReadingFile, OD_T("Error reading file"))
		OD_ERROR_DEF(eSecErrorWritingFile, OD_T("Error writing file"))
		OD_ERROR_DEF(eSecErrorWritingSignature, OD_T("Error writing signature"))
		OD_ERROR_DEF(eSecInitializationFailure, OD_T("Initialization failure"))
		OD_ERROR_DEF(eSecInvalidDigitalId, OD_T("Invalid digital id"))
		OD_ERROR_DEF(eLoadFailed, OD_T("Load failed"))
		OD_ERROR_DEF(eSubSelectionSetEmpty, OD_T("SubSelectionSet empty"))
		OD_ERROR_DEF(eUnableToGetLabelBlock, OD_T("Unable to get label Block"))
		OD_ERROR_DEF(eUnableToGetViewAssociation, OD_T("Unable to get View association"))
		OD_ERROR_DEF(eUnableToRemoveAssociation, OD_T("Unable to remove association"))
		OD_ERROR_DEF(eUnableToSetLabelBlock, OD_T("Unable to set label Block"))
		OD_ERROR_DEF(eUnableToSetViewAssociation, OD_T("Unable to set View association"))
		OD_ERROR_DEF(eUnableToSyncModelView, OD_T("Unable to sync Model View"))
		OD_ERROR_DEF(eUnsupportedFileFormat, OD_T("Unsupported file format"))
		OD_ERROR_DEF(eUserBreak, OD_T("User break"))
		OD_ERROR_DEF(eWasNotErased, OD_T("Was not erased"))
		OD_ERROR_DEF(eWrongCellType, OD_T("Wrong cell type"))
		OD_ERROR_DEF(eTxError, OD_T("Tx application error"))
		OD_ERROR_DEF(eHiddenLayerNotAllowed, OD_T("Hidden Layer not allowed"))
		OD_ERROR_DEF(eInvalidLicense, OD_T("Invalid license"))
		OD_ERROR_DEF(eIncorrectDatabaseType, OD_T("Invalid database type"))
		OD_ERROR_DEF(eInvalidCategory, OD_T("Invalid category"))

		OD_ERROR_DEF(eCryptProviderUnavailable, OD_T("The cryptography service provider \"%ls\" used to protect this drawing is not installed on this computer"))
		OD_ERROR_DEF(eInvalidNumPCurves, OD_T("The number of curves does not match with the number of parameter-space curves"))
		OD_ERROR_DEF(eNoTrimmigLoop, OD_T("Trimming loop is undefined"))
		OD_ERROR_DEF(eBrokenTrimmingLoop, OD_T("Edges are not ordered"))
		OD_ERROR_DEF(eBadApexLoop, OD_T("Bad loop in apex"))
		OD_ERROR_DEF(eLoopNotClosed, OD_T("Trimming loop must be closed"))
		OD_ERROR_DEF(eLoopIsNotOnFace, OD_T("Trimming loop is not placed on the face"))
		OD_ERROR_DEF(eLoopSelfIntersecting, OD_T("Self-intersecting trimming loop"))
		OD_ERROR_DEF(eInvalidIntervals, OD_T("Intervals of 3d curves differ from their parameter-space curves intervals"))
		OD_ERROR_DEF(eEmptySet, OD_T("Set of elements is empty"))
		OD_ERROR_DEF(eInfinite, OD_T("Infinite / unbounded object"))

		OD_ERROR_DEF(eDataTooLarge, OD_T("Uncompressed object size is too large to be saved to specified .dwg version"))

		OD_ERROR_DEF(eSyntaxError, OD_T("Syntax error"))
		OD_ERROR_DEF(eDisabledInConfig, OD_T("Disabled for this platform or configuration"))
		OD_ERROR_DEF(eCantSetEnvVar, OD_T("Can not set environment variable"))
		OD_ERROR_DEF(eInvalidSurface, OD_T("Invalid surface"))
		OD_ERROR_DEF(eInvalidOrientation, OD_T("Invalid orientation"))
		OD_ERROR_DEF(eLoopsIntersecting, OD_T("Loops intersect"))
		OD_ERROR_DEF(eInvalidEdge, OD_T("Invalid edge"))
		OD_ERROR_DEF(eNullEdgeCurve, OD_T("Null edge curve"))
		OD_ERROR_DEF(eNullFaceSurface, OD_T("Null face surface"))
		OD_ERROR_DEF(eStartOrEndPntNotSet, OD_T("Start or end point of edge not set"))
		OD_ERROR_DEF(eIntervalIsTooShort, OD_T("Interval is too short"))
		OD_ERROR_DEF(eCurveLengthIsTooShort, OD_T("Length of curve is too short"))
		OD_ERROR_DEF(eCurveEndsMissed, OD_T("Curve ends missed"))
		OD_ERROR_DEF(ePointNotOnCurve, OD_T("Point not on curve"))
		OD_ERROR_DEF(eInvalidProps, OD_T("Invalid properties of the object"))
		OD_ERROR_DEF(eInvalidCurve, OD_T("Invalid curve"))
		OD_ERROR_DEF(eDiscontinuousCurve, OD_T("Discontinuous curve"))
		OD_ERROR_DEF(eParamHasNoValue, OD_T("The parameter does not have a value"))

		OD_ERROR_DEF(eBrFileMissed, OD_T("Brep File missed"))
		OD_ERROR_DEF(eBrBrepMissed, OD_T("Brep missed"))
		OD_ERROR_DEF(eBrComplexMissed, OD_T("Brep Complex missed"))
		OD_ERROR_DEF(eBrShellMissed, OD_T("Brep Shell missed"))
		OD_ERROR_DEF(eBrFaceMissed, OD_T("Brep Face missed"))
		OD_ERROR_DEF(eBrLoopMissed, OD_T("Brep Loop missed"))
		OD_ERROR_DEF(eBrEdgeMissed, OD_T("Brep Edge missed"))
		OD_ERROR_DEF(eBrVertexMissed, OD_T("Brep Vertex missed"))
		OD_ERROR_DEF(eBrEmptyLoop, OD_T("Brep empty Loop"))
		OD_ERROR_DEF(eCellNotFound, OD_T("Cell not found"))
		OD_ERROR_DEF(eInvalidElementState, OD_T("Invalid element state"))
		OD_ERROR_DEF(eNoIntersections, OD_T("No intersections"))
		OD_ERROR_DEF(eMSmemcpySecureInvalidParameter, OD_T("Invalid parameter passed to memcpy_s"))
		OD_ERROR_DEF(eMSmemmoveSecureInvalidParameter, OD_T("Invalid parameter passed to memmove_s"))

		OD_ERROR_DEF(eDaiInternalError, OD_T("DAI internal error"))
		OD_ERROR_DEF(eIncorrectSchema, OD_T("Incorrect schema"))
		OD_ERROR_DEF(eUnsupportedSchema, OD_T("Unsupported schema"))
		OD_ERROR_DEF(eEmptyRepository, OD_T("Empty repository"))

		OD_ERROR_DEF(eFailedToEvaluate, OD_T("Failed to evaluate"))
		OD_ERROR_DEF(eFailedToEvaluateDependents, OD_T("Failed to evaluate dependents"))
		OD_ERROR_DEF(eInvalidExpression, OD_T("Invalid expression"))
		OD_ERROR_DEF(eCyclicDependency, OD_T("Cyclic dependency"))
#define eCannotBeErased eCannotBeErasedByCaller
		eDummyLastError
    };

    public ref class Entity : public DisposableWrapper
    {
    protected:
        OdDbEntity* GetImpObj()
        {
            return static_cast<OdDbEntity*>(DisposableWrapper::GetImpObj());
        }
    public:
		static unsigned int Create(String^ desc);
        Entity(OdDbEntity* nativeEntity, bool autoDelete) : DisposableWrapper(IntPtr(nativeEntity), autoDelete)
        {
        }
        property Scale3d Scale
        {
            Scale3d get();
            void set(Scale3d value);
        }

        property Point3d Position
        {
            Point3d get();
            void set(Point3d value);
        }

        property Vector3d XDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Vector3d YDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Vector3d ZDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Matrix3d Transform
        {
            Matrix3d get();
        }

        property bool IsVisible
        {
            bool get();
            void set(bool value);
        }

        property bool IsSelected
        {
            bool get();
            void set(bool value);
        }

        property Extents3d Extents
        {
            Extents3d get();
        }

        MathResult TransformBy(Matrix3d xform);
        virtual String^ ToJson();
        static unsigned int FromJson(String^ json);
		void Draw();
    };
}

